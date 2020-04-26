R"JS(
/** Helper fn to work with slow server */
async function fetchAndResend(uri, created = (window.performance.timing.navigationStart + window.performance.now()) % 1_000_000_000) {
    await fetch(`${uri}&created=${created}`).catch(async () =>
        await fetchAndResend(uri, created)
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

    document.querySelector(".alert").addEventListener("click", () => {
        document.querySelector(".alert").setAttribute("hidden", "true");
    });
    setInterval(async () => {
        const res = await fetch(`/button`);
        if (await res.text() === "yes") {
            document.querySelector(".alert").removeAttribute("hidden");
        }
    }, 10000);
};
)JS"