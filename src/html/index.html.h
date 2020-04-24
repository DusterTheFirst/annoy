R"HTML(
<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Zach Annoyinator 9001!!!</title>
        <script>
            window.onload = () => {
                document.getElementById("rgb-led-color").onchange = (e) => {
                    console.log(e.target.value);
                }

                const defconLabel = document.getElementById("DEFCONLabel");
                document.getElementById("DEFCONLevel").oninput = (e) => {
                    defconLabel.innerText = e.target.value;
                };
            };
        </script>
        <style>
            input[type=range] {
                direction: rtl;
            }
        </style>
    </head>
    <body>
        <label>
            RGB LED Color:
            <input type="color" id="rgb-led-color" />
        </label>
        <label>
            DEFCON Level: <div id="DEFCONLabel">5</div>
            <input type="range" min="1" max="5" value="5" id="DEFCONLevel" />
        </label>

        <button>Strobe</button>
        <button>Blue</button>
    </body>
</html>
)HTML"