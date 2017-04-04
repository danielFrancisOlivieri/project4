var XMLHttp, getCommentListBusy = false,
    toPreventRepitition = "";

// intializes the site 
function init() {
    if (navigator.appName == "Microsoft Internet Explorer") {
        XMLHttp = new ActiveXObject("Microsoft.XMLHTTP");
    } else {
        XMLHttp = new XMLHttpRequest();
    }
}
// gets comments from the server 
function getCommentList() {

    if (!getCommentListBusy) {

        getCommentListBusy = true;
        var commentClass = "comment";
        var message = "***$request$END"; // message request

        XMLHttp.open("POST", "/cgi-bin/olivierid_JAD_chatAjax.cgi?" // sends the post request 
            +
            "message=" + message, true);

        XMLHttp.onreadystatechange = function() {
            if (XMLHttp.readyState == 4) { // this determines whether the XMLHttp better

                var fromCGI = XMLHttp.responseText;

                // replaces certain words 
                fromCGI = fromCGI.replace("$END", "");
                fromCGI = fromCGI.replace("Daniel", "my hero Daniel");
                fromCGI = fromCGI.replace("fuck", "f***");
                fromCGI = fromCGI.replace("Juvi", "the programmer formerly know as Juvi");
                fromCGI = fromCGI.replace("Aidan", "Alexander Hamilton");


                if ((toPreventRepitition != fromCGI) && ("$END" != fromCGI)) {
                    console.log(toPreventRepitition + "  fromcgi: " + fromCGI);
                    $("#chatbox").append(fromCGI); //adds to the chatbox

                    // there was a bug when blank messages ruined it, this prevents it 
                    if (fromCGI.length > 2) // makes sure it's a real message 
                    {
                        toPreventRepitition = fromCGI;
                    }
                }

                getCommentListBusy = false; // sets it back to free and open 
            }
        }
        XMLHttp.send(null);

    }

}

var intVar;
// runs the commentlist function 
function AutoRefresh() {


    intVar = setInterval(function() {
        getCommentList()
    }, 100);
}

function StopRefresh() {
    clearInterval(intVar);
}

function getUsername() // gets the username from the input and puts it into the welcome 
{

    var name = document.getElementById('userName').value;
    document.getElementById('user').innerHTML = name;
    commentObject.username = name;
    $(".welcome").css("visibility", "visible"); // sets it to visible 
}



// comment object
var commentObject = {
    username: "Hamlet",
    text: "",
    color: "black",
    returnOutputString: function() {
        return "$USERNAME*" + this.username + "Cato$COLOR*" + this.color + "$PICTURE*three$TEXT*" + this.text + "$END";
    }

}

var XMLHttp, avoidReplication = "";
if (navigator.appName == "Microsoft Internet Explorer") {
    XMLHttp = new ActiveXObject("Microsoft.XMLHTTP");
} else {
    XMLHttp = new XMLHttpRequest();
}

// sends comments 
function sendComment() {

    var message = document.getElementById('usermsg').value;


    if (message.length > 1) {

        commentObject.text = message;
        message = commentObject.username + ": " + message + "$END";

        XMLHttp.open("GET", "/cgi-bin/olivierid_JAD_chatAjax.cgi?" +
            "message=" + message, true);

        XMLHttp.send(null);

    }
}

// this allows the user log out 
$(document).ready(function() {
    $("#exit").click(function() {
        document.getElementById('userName').disabled = false;
        alert("Do you want to Log Out? This will delete the chats.");
        $(".comment").hide();
        $("input").prop('disabled', true);
    });

});


// readies autorefresh 
$(document).ready(function() {
    AutoRefresh();
});
