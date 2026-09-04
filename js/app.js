const map = L.map("map").setView([43.7, -79.4], 9);

L.tileLayer(
    "https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png",
    {
        attribution: "&copy; OpenStreetMap contributors"
    }
).addTo(map);

const myStationMarker = L.marker([43.7, -79.4]).addTo(map);

myStationMarker.bindPopup("<b>VE3RER</b><br>Home station");