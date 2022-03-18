var volume_up = document.createElement("button");
var volume_down = document.createElement("button");
var toggle_power = document.createElement("button");

volume_up.innerText = "VOL +";
volume_down.innerText = "VOL -";
toggle_power.innerText = "ON/OFF";

function toggle_handler () {
    console.log(this.responseText);
}

toggle_power.addEventListener("click", () => {
    var req = new XMLHttpRequest();
    req.addEventListener("load", toggle_handler);
    req.open("GET", "http://localhost:9090/volume/up");
    req.setRequestHeader("Access-Control-Allow-Origin", "*");
    req.send();
});

// Components behind each functionality:
// - Button
// - Label (innerText)
// - handler (set banner text + color)
// - Click handler (just uses API endpoint)
// - ID
// - Addition to document

toggle_power.id = "toggle";

document.body.appendChild(toggle_power);
