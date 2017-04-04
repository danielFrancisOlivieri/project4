
     var XMLHttp, getCommentListBusy = false, toPreventRepitition = "";


	 function init() {
    if(navigator.appName == "Microsoft Internet Explorer") {
	XMLHttp = new ActiveXObject("Microsoft.XMLHTTP");
    } else {
	XMLHttp = new XMLHttpRequest();
    }
}

$("#usermsg").keypress(function(e) {
    if(e.which == 13) {
       alert("What kills you in this life will be your mother in the next.");
    }
});


function getCommentList () {

 if (!getCommentListBusy)
 {

 getCommentListBusy = true;
 var commentClass = "comment";
   var message = "***$request$END"; 

    XMLHttp.open("POST", "/cgi-bin/olivierid_JAD_chatAjax.cgi?"
						 + "message=" + message
		 ,true);
		 
		 /*
		 the next step is to go through this very carefully and try to make it as simple and functional as the other one
		 The issue is in the XMLHttp
		  
		 */
    XMLHttp.onreadystatechange=function() {
	if (XMLHttp.readyState == 4) {
	
		       var fromCGI = XMLHttp.responseText;
			  			   

	fromCGI = fromCGI.replace("$END", "");
	fromCGI = fromCGI.replace("Daniel", "my hero Daniel");
	fromCGI = fromCGI.replace("fuck", "f***");
	fromCGI = fromCGI.replace("Juvi", "the programmer formerly know as Juvi");
	fromCGI = fromCGI.replace("Aidan", "Alexander Hamilton");
	//$('.comment').remove();
	
	if ((toPreventRepitition != fromCGI) && ("$END" != fromCGI))
	{
	console.log (toPreventRepitition + "  fromcgi: " + fromCGI);
	$("#chatbox").append(fromCGI);   //adds to the chatbox
		if (fromCGI.length > 2)
		{
			toPreventRepitition = fromCGI;
		}
	
	}
	
	getCommentListBusy = false;
	}
    }
    XMLHttp.send(null);
	
 }
  
}

var intVar;
function AutoRefresh() {


    intVar = setInterval(function(){ getCommentList()}, 100);
}

function StopRefresh() {
    clearInterval(intVar);
}




     function getUsername()
     {

     var name= document.getElementById('userName').value;
     document.getElementById('user').innerHTML = name;
commentObject.username = name;
	$(".welcome").css("visibility", "visible");
      }



// comment object
var commentObject = {
username : "Hamlet",
text: "",
color: "black",
returnOutputString: function() {
 return "$USERNAME*" + this.username + "Cato$COLOR*" + this.color + "$PICTURE*three$TEXT*" + this.text + "$END";
}

}

var XMLHttp, avoidReplication = "";
if(navigator.appName == "Microsoft Internet Explorer") {
    XMLHttp = new ActiveXObject("Microsoft.XMLHTTP");
} else {
    XMLHttp = new XMLHttpRequest();
}


function sendComment () {

 var message = document.getElementById('usermsg').value;


if (message.length > 1)
{

  // if (name.length < 1) return;

  commentObject.text = message;
  message = commentObject.username + ": " + message + "$END";
  //inMessage = commentObject.returnOutputString();

    XMLHttp.open("GET", "/cgi-bin/olivierid_JAD_chatAjax.cgi?"
						 + "message=" + message
						 ,true);
						

	XMLHttp.send(null);

}
}

$(document).ready(function(){
    $("#exit").click(function(){
     document.getElementById('userName').disabled = false;
	 alert("Do you want to Log Out? This will delete the chats.");
	  $(".comment").hide();
	  $("input").prop('disabled', true);
    });
  
});

// function logOut()
				// {
				 
				 // document.getElementById('userName').disabled = false;
				 
				 // alert("Do you want to Log Out? This will delete the chats.");
				 
				 // /*if(confirm("Do you want to Log Out? This will delete the chats."))
   				 // document.forms[0].submit();
 				 // else
 				   // return false; */
 				   
				 // var div = document.getElementById('chatbox');
				 // div.style.visibility= 'hidden';
				 
				// }
  

    
		       

		       
			   
$( document ).ready(function() {
    AutoRefresh();
});
