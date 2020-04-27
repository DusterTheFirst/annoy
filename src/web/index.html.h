R"HTML(
<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Zach Annoyinator 9001!!!</title>
        <script src="/scripts.js"></script>
        <link rel="stylesheet" href="/styles.css">
    </head>
    <body>
        <div class="alert" hidden>Zach has responded to your message! Click to dismiss</div>
        <label class="rgb">
            RGB LED Color:
            <input type="color" />
        </label>
        <label class="defcon">
            DEFCON Level: <span>5</span>
            <input type="range" min="1" max="5" value="5" />
        </label>

        <button id="strobe">Strobe</button>
        <button id="blueLight">Blue</button>
    </body>
</html>
)HTML"