var volume_up = document.createElement("button");
var volume_down = document.createElement("button");
var toggle_power = document.createElement("button");

volume_up.innerText = "VOL +";
volume_down.innerText = "VOL -";
toggle_power.innerText = "⏻";

toggle_power.addEventListener("click", () => {
    alert("toggling power");

});

toggle_power.id = "toggle";

document.body.appendChild(toggle_power);
