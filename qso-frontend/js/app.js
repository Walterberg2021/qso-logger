const map = L.map("map").setView([43.7, -79.4], 9);

L.tileLayer(
    "https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png",
    {
        attribution: "&copy; OpenStreetMap contributors"
    }
).addTo(map);

const myStationMarker = L.marker([43.7, -79.4]).addTo(map);

myStationMarker.bindPopup("<b>VE3RER</b><br>Home station");

// submit qso form
const qsoForm = document.getElementById("qso-form");

const callSignPattern = /^[A-Z0-9]+(?:\/[A-Z0-9]+)*$/;
const gridPattern = /^[A-R]{2}([0-9]{2}([A-X]{2}([0-9]{2})?)?)?$/;

qsoForm.addEventListener("submit", function (event) {
    event.preventDefault();

    console.log("Form submitted");

    const callsign = document.getElementById("callsign")
        .value
        .trim()
        .toUpperCase();
    console.log(callsign);


    if (!callSignPattern.test(callsign)) {
        console.log("Invalid callsign.");
        return;
    }

    const grid = document.getElementById("grid")
        .value
        .trim()
        .toUpperCase();
    console.log(grid);

    if (grid !== "" && !gridPattern.test(grid)) {
        console.log("Invalid grid");
        return;
    }

    const frequency = parseFloat(document.getElementById("frequency").value);
    console.log(frequency);

    if (isNaN(frequency) || frequency <= 0) {
        console.log("Invalid frequency");
        return;
    }

    const mode = document.getElementById("mode").value;

    if (mode === "") {
        console.log("Invalid mode");
        return;
    }

    const txRst = document.getElementById("rstTx").value.trim();
    const rxRst = document.getElementById("rstRx").value.trim();

    const notes = document.getElementById("notes").value.trim();

    const dateTime = getCurrentUtcDateTime();
    console.log(dateTime);

    const qso = {
        corCall: callsign,
        corGrid: grid,
        frequency,
        mode,
        txRst,
        rxRst,
        notes,
        dateTime
    };

    console.log(qso);

    const qsoJson = JSON.stringify(qso);
    console.log(qsoJson);

    console.log("About to send:", qsoJson);

    fetch("http://localhost:8080/api/qso", {
        method: "POST",
        headers: {
            "Content-Type": "application/json"
        },
        body: qsoJson
    })
    .then(response => {
        console.log("Server status:", response.status);
    })
    .catch(error => {
        console.error("Fetch failed:", error);
    });

});

function getCurrentUtcDateTime() {
    const now = new Date();

    return {
        year: now.getUTCFullYear(),
        month: now.getUTCMonth() + 1,
        day: now.getUTCDate(),
        hour: now.getUTCHours(),
        minute: now.getUTCMinutes(),
        second: now.getUTCSeconds()
    };
}
