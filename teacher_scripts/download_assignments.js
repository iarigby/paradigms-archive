function getAssignments() {
    return Array.from(document.getElementsByClassName("WkZsyc"))
        .filter(e => {
            const turned_in = Array.from(e.getElementsByClassName("vzcr8"))
            if (turned_in.length > 0) return turned_in[0].innerHTML.includes("Turned in")
            else return false })
}

function getAssignmentLink(elem) {
    return Array.from(elem.getElementsByClassName("maXJsd"))[1].href
}
function extractId(driveUrl) {
    const rx = /https:\/\/drive.google.com\/open\?id=(.*)&authuser=0/
    const res = rx.exec(driveUrl)
    return res[1]
}

function createDownloadLink(id) {
    return `https://drive.google.com/a/freeuni.edu.ge/uc?authuser=0&id=${id}&export=download`
}

function main() {
    const urls = getAssignments()
          .map(getAssignmentLink)
          .map(extractId)
          .map(createDownloadLink)
    for (let i = 1; i <= urls.length; i++) {
        (function(index) {
            setTimeout(function() {
                console.log(`donwloading assignment ${index}`)
                window.location.href = urls[index]}, i*5000);
        })(i);
    }
}
