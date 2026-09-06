const map = L.map("map").setView([43.7, -79.4], 9);

L.tileLayer(
    "https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png",
    {
        attribution: "&copy; OpenStreetMap contributors"
    }
).addTo(map);

const myStationMarker = L.marker([43.7, -79.4]).addTo(map);

myStationMarker.bindPopup("<b>VE3RER</b><br>Home station");

//form
function getBandFromFrequency(frequency) {
    if (frequency >= 0.1357 && frequency <= 0.1378) return "2200m";
    if (frequency >= 0.472 && frequency <= 0.479) return "630m";
    if (frequency >= 1.8 && frequency <= 2.0) return "160m";
    if (frequency >= 3.5 && frequency <= 4.0) return "80m";
    if (frequency >= 5.3 && frequency <= 5.4) return "60m";
    if (frequency >= 7.0 && frequency <= 7.3) return "40m";
    if (frequency >= 10.1 && frequency <= 10.15) return "30m";
    if (frequency >= 14.0 && frequency <= 14.35) return "20m";
    if (frequency >= 18.068 && frequency <= 18.168) return "17m";
    if (frequency >= 21.0 && frequency <= 21.45) return "15m";
    if (frequency >= 24.89 && frequency <= 24.99) return "12m";
    if (frequency >= 28.0 && frequency <= 29.7) return "10m";
    if (frequency >= 50 && frequency <= 54) return "6m";
    if (frequency >= 144 && frequency <= 148) return "2m";
    if (frequency >= 430 && frequency <= 450) return "70cm";
    if (frequency >= 902 && frequency <= 928) return "33cm";

    return null;
}

const qsoForm = document.getElementById("qso-form");

function isValidCallsign(callsign) {
    const pattern = /^[A-Z0-9]{1,3}[0-9][A-Z0-9]{1,4}$/;
    return pattern.test(callsign);
}

function isValidGrid(grid) {
    const pattern = /^[A-R]{2}[0-9]{2}([A-X]{2})?$/;
    return pattern.test(grid);
}

function showError(message) {
    alert(message);
}

qsoForm.addEventListener("submit", function (event) {
    event.preventDefault();

    const callsign = document
        .getElementById("callsign")
        .value
        .trim()
        .toUpperCase();

    const grid = document
        .getElementById("grid")
        .value
        .trim()
        .toUpperCase();

    const frequency = parseFloat(
        document.getElementById("frequency").value
    );

    const selectedBand = document.getElementById("band").value;

    const mode = document.getElementById("mode").value;

    const rst = document
        .getElementById("rst")
        .value
        .trim();

    const notes = document
        .getElementById("notes")
        .value
        .trim();

    if (!isValidCallsign(callsign)) {
        showError("Invalid callsign.");
        return;
    }

    if (!isValidGrid(grid)) {
        showError("Invalid Maidenhead grid locator.");
        return;
    }

    if (Number.isNaN(frequency)) {
        showError("Enter a valid frequency.");
        return;
    }

    const detectedBand = getBandFromFrequency(frequency);

    if (detectedBand === null) {
        showError("Frequency is outside the supported amateur bands.");
        return;
    }

    let band = selectedBand;

    if (band === "") {
        band = detectedBand;
    }

    if (selectedBand !== "" && selectedBand !== detectedBand) {
        showError(
            `Frequency ${frequency} MHz belongs to ${detectedBand}, not ${selectedBand}.`
        );
        return;
    }

    const qso = {
        callsign,
        grid,
        frequency,
        band,
        mode,
        rst,
        notes
    };

    console.log(qso);
});