R"JS(
/** Helper fn to work with slow server */
async function fetchAndResend(uri, created = (window.performance.timing.navigationStart + window.performance.now()) % 1_000_000_000) {
    await fetch(`${uri}&created=${created}`).catch(async () =>
        await fetchAndResend(uri, created)
    )
}

window.onload = async () => {
    // Setup RGB Led
    const rgbLed = document.querySelector(".rgb input");
    const updateRgbLed = async () => {
        await fetchAndResend(`/act?rgb=${rgbLed.value.substring(1)}`);
    };
    rgbLed.onchange = updateRgbLed;
    await updateRgbLed();

    // Setup defcon
    const defconContainer = document.querySelector(".defcon");
    const defconLabel = defconContainer.querySelector("span");
    const defconLevel = defconContainer.querySelector("input");
    const defconUpdate = async () => {
        defconContainer.style.backgroundColor = {
            "1": "#fe0000",
            "2": "#800000",
            "3": "#808000",
            "4": "#80fe00",
            "5": "#00fe00"
        }[defconLevel.value];
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

    // Setup alert
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
// )JS"