var btnAlarm = document.getElementById("btnAlarm");
btnAlarm.onclick = function () {
    var xml = new XMLHttpRequest();
    xml.open("GET", "/Home/setAlarm?status=" + (btnAlarm.textContent === "On" ? "false" : "true"));
    xml.send();
};

var evtAlarm = new EventSource("/Home/SyncAlarm");
evtAlarm.onmessage = function (e) {
    var data = e.data.replace("data: ", "");
    data = data.replace("\n\n", "");
    btnAlarm.textContent = data;
    if (data === "On") {
        btnAlarm.classList.remove("btn-danger");
        btnAlarm.classList.add("btn-success");
    } else {
        btnAlarm.classList.remove("btn-success");
        btnAlarm.classList.add("btn-danger");
    }
};