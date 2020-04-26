R"HTML(
<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Zach Annoyinator 9001!!!</title>
        <script>
            /** Helper fn to work with slow server */
            async function fetchAndResend(uri) {
                await fetch(uri).catch(async (e) =>
                    await fetchAndResend(uri)
                )
            }

            window.onload = async () => {
                // Setup RGB Led
                const rgbLed = document.getElementById("rgb-led-color");
                const updateRgbLed = async () => {
                    await fetchAndResend(`/act?rgb=${rgbLed.value.substring(1)}`);
                };
                rgbLed.onchange = updateRgbLed;
                await updateRgbLed();

                // Setup defcon
                const defconLabel = document.getElementById("DEFCONLabel");
                const defconLevel = document.getElementById("DEFCONLevel");
                const defconUpdate = async () => {
                    defconLabel.innerText = defconLevel.value;
                    await fetchAndResend(`/act?defcon=${defconLevel.value}`);
                };
                defconLevel.oninput = defconUpdate;
                await defconUpdate();

                // Setup strobe
                document.getElementById("strobe").onclick = async (e) => {
                    await fetchAndResend("/act?strobe=true");
                }

                // Setup blue strobe
                document.getElementById("blueLight").onclick = async (e) => {
                    await fetchAndResend("/act?blueStrobe=true");
                }
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

        <button id="strobe">Strobe</button>
        <button id="blueLight">Blue</button>
    </body>
</html>
)HTML"