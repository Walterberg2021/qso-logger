const map = L.map("map").setView([43.7, -79.4], 9);

L.tileLayer(
    "https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png",
    {
        attribution: "&copy; OpenStreetMap contributors"
    }
).addTo(map);

const stationMarker = L.marker([43.7, -79.4]).addTo(map);

stationMarker.bindPopup("<b>VE3RER</b><br>Home station");