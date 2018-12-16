var dens = document.getElementsByClassName("den");
var index;
var key;
for (var i = 0; i < dens.length; i++) {
    dens[i].onclick = function () {
        var xml = new XMLHttpRequest();
        index = parseInt(this.dataset.index);
        key = this.dataset.key;
        xml.onreadystatechange = function (data) {
            if (this.readyState === 4 && this.status === 200) {
                var res = data.currentTarget.responseText;
                if (res.search("Error:") > -1) {
                    res = res.replace("Error:", "");
                    alert(res);
                }
            }
        };
        xml.open("POST", "/Home/setDen", true);
        xml.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
        xml.send("key=" + key);
    };
}

var syncden = new EventSource("/Home/SyncDens");
syncden.onmessage = function (e) {
    var data = e.data.replace("data: ", "");
    data = data.replace("\n\n","");
    var den = data.split("-");
    var numDen = parseInt(den[0]);
    dens[numDen].textContent = den[1];
    if (dens[numDen].textContent === "On") {
        dens[numDen].classList.remove("btn-danger");
        dens[numDen].classList.add("btn-success");
    } else {
        dens[numDen].classList.remove("btn-success");
        dens[numDen].classList.add("btn-danger");
    }
};