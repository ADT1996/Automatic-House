if (typeof (EventSource) !== "undefined") {
    var evt = new EventSource("/Home/NhietDoDoAm");
    var doam = document.getElementById("doam");
    var nhietdo = document.getElementById("nhietdo");
    evt.onmessage = function (e) {
        //var mess = JSON.parse(e.data);
        //nhietdo.innerText = mess.nhietdo;
        //doam.innerText = mess.doam;
        var data = e.data.replace("data: ", "");
        data = data.replace("\n\n","");
        var values = data.split('-');
        nhietdo.innerText = values[0];
        doam.innerText = values[1];
    };
    evt.onerror = function (e) {
        console.log(e);
        console.log(evt.readyState);
        //evt.close();
    };
    evt.onopen = function () {
        console.log("Event source starting...");
    };


} else {
    console.log("EventSource is undefined");
}
window.onclose = function () {
    evt.close();
};