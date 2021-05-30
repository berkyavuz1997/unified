#pragma once

#include <Arduino.h>

const String DEVICE_NAME = "Rasputin";
const String BASE_HTML = "<!DOCTYPE html> <html> <body> <style> body { font-family: \"Courier New\", Courier, monospace; } .container { margin: auto; width: 80%; position: relative; } .header { text-align: center; } .content_container { display: grid; } .img { display: block; min-width: 50%; grid-column-start: 0; grid-column-end: 4; } .lidar { grid-column-start: 4; grid-column-end: 5; } .btn_wrapper { text-align: center; } .scenario { text-align: center; } .btn { display: inline-block; background: #000; border-radius: 4px; font-family: \"Courier New\", Courier, monospace; font-size: 14px; color: #fff; padding: 8px 12px; cursor: pointer; } </style> <div class=\"container\"> <h1 class=\"header\">RoboCoRS - Rasputin</h1> <div class=\"content_container\"> <img class=\"img\" src=\"data:image/gif;base64,\" /> <div class=\"lidar\"> <h3>Lidar Data</h3> <div class=\"lidar_data\"></div> </div> </div> <h2 class=\"scenario\"></h2> <form action=\"/scenario\"> <h3>Select Scenario</h3> <input type=\"radio\" id=\"Stop Execution\" name=\"index\" value=\"0\" /> <label for=\"Stop Execution\"> Stop Execution </label> <br /> <input type=\"radio\" id=\"Target Identification and Transition with One Robot\" name=\"index\" value=\"1\" /> <label for=\"Target Identification and Transition with One Robot\"> Target Identification and Transition with One Robot </label> <br /> <input type=\"radio\" id=\"Pioneer Robot Following\" name=\"index\" value=\"2\" /> <label for=\"Pioneer Robot Following\"> Pioneer Robot Following </label> <br /> <input type=\"radio\" id=\"Target Identification and Locating with Three Robots\" name=\"index\" value=\"3\" /> <label for=\"Target Identification and Locating with Three Robots\"> Target Identification and Locating with Three Robots </label> <br /> <input type=\"radio\" id=\"Target Identification and Transition with Three Robots While Avoiding Obstacles\" name=\"index\" value=\"4\" /> <label for=\"Target Identification and Transition with Three Robots While Avoiding Obstacles\"> Target Identification and Transition with Three Robots While Avoiding Obstacles </label> <br /> <input type=\"radio\" id=\"Hostile Target Detection and Avoiding\" name=\"index\" value=\"5\" /> <label for=\"Hostile Target Detection and Avoiding\"> Hostile Target Detection and Avoiding </label> <br /> <div class=\"btn_wrapper\"> <input type=\"submit\" value=\"Submit\" class=\"btn\" /> </div> </form> </div> <script> const scenarios = [ \"Stop Execution\", \"Target Identification and Transition with One Robot\", \"Pioneer Robot Following\", \"Target Identification and Locating with Three Robots\", \"Target Identification and Transition with Three Robots While Avoiding Obstacles\", \"Hostile Target Detection and Avoiding\", ]; async function updateLidar() { const response = await fetch(\"/lidar\"); const text = await response.text(); const data = text.split('*').map(part => part.split('-')); let html = \"\"; data.forEach(d => html += `<p><strong>${d[0]}:</strong> ${d[1]} mm at ${d[2]} degree angle</p>`); const lidar = document.querySelector(\".lidar_data\"); lidar.innerHTML = html; } async function updateImage() { const response = await fetch(\"/pic\"); const text = await response.text(); const img = document.querySelector(\".img\"); img.src = `data:image/gif;base64,${text}`; } async function update() { const image = updateImage(); const lidar = updateLidar(); await Promise.all(image, lidar); } function start() { const interval = setInterval(update, 100); return () => clearInterval(interval); } function updateScenario() { const queryString = window.location.search; const urlParams = new URLSearchParams(queryString); if (!urlParams.has(\"index\")) return; const index = parseInt(urlParams.get(\"index\")); if (index >= scenarios.length) return; const scenarioName = scenarios[index]; const btn = document.getElementById(scenarioName); btn.checked = true; if (index > 0) { const h2 = document.querySelector(\".scenario\"); h2.innerHTML = `Current Scenario - ${scenarioName}`; } } updateScenario(); const stop = start(); </script> </body> </html>";