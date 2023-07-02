function save_button_click() {
	var s1;
	var s2;	
	
	s1 = document.getElementById("MB_SPEED").value;
	s2 = document.getElementById("MB_ADDRESS").value;
	
	var x = new XMLHttpRequest();
	x.open("GET", "/save?s1=" + s1 + '&s2=' + s2, true);
	x.onload = function (){
    alert( x.responseText);	
}
x.send(null);	

document.getElementById("save_button").innerText = "Сохранено";
}

function reset_save_button() {
document.getElementById("save_button").innerText = "Сохранить";
}


