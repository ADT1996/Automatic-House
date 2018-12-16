var btns = document.getElementsByClassName("btn");
var i;
for (i = 0; i < btns.length; i++) {
    if (btns[i].textContent === "On") {
        btns[i].className += " btn-success";
    } else {
        btns[i].className += " btn-danger";
    }
}