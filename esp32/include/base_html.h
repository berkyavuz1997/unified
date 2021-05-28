#pragma once

#include <Arduino.h>

const String base_html =
    "<!DOCTYPE html> <html> <body> <img src=\"data:image/gif;base64,\" /> "
    "<script> async function update() { const response = await "
    "fetch(\"http://192.168.4.1/pic\"); const text = await response.text(); "
    "const img = document.getElementById(\"img\"); img.src = "
    "`data:image/gif;base64,${text}`; } function start() { const interval = "
    "setInterval(update, 100); return () => clearInterval(interval); } const "
    "stop = start(); </script> </body> </html>";
