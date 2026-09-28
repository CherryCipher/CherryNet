#pragma once

namespace Pages
{
    static constexpr char INDEX[] = R"rawliteral(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">

    <title>CherryNet</title>

    <style>
        body {
            margin: 0;
            padding: 20px;
            background: #111;
            color: #fff;
            font-family: Arial, sans-serif;
        }

        .container {
            max-width: 600px;
            margin: auto;
        }

        .card {
            background: #1d1d1d;
            padding: 20px;
            border-radius: 10px;
            margin-bottom: 15px;
        }
    </style>
</head>

<body>

<div class="container">

    <h1>CherryNet</h1>

    <div class="card">
        <h2>Device</h2>
        <div id="status">Loading...</div>
    </div>

</div>

<script>
async function updateStatus()
{
    try
    {
        const response = await fetch("/api/status");
        const data = await response.json();

        document.getElementById("status").innerText =
            data.device + " - " + data.status;
    }
    catch (error)
    {
        document.getElementById("status").innerText =
            "Device unavailable";
    }
}

updateStatus();
</script>

</body>
</html>
)rawliteral";

    static constexpr char ERROR404[] = R"rawliteral(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">

    <title>404</title>
</head>

<body>

    <h1>404</h1>
    <p>Page not found.</p>

</body>

</html>
)rawliteral";
}