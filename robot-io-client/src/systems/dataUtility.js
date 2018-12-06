

export default {
    Download,
    UploadAsync
}


function Download(data) {
    const name = data.name === undefined ? "data" : data.name
    const dataStr = JSON.stringify(data)
    const elt = document.createElement('a')
    elt.setAttribute('href', 'data:application/json;charset=utf-8,' + encodeURIComponent(dataStr))
    elt.setAttribute('download', name + '.json')
    elt.style.display = 'none'
    document.body.appendChild(elt)
    elt.click()
    document.body.removeChild(elt)
}

function UploadAsync() {
    return new Promise((resolve, reject) => {
        const elt = document.createElement('input')
        elt.setAttribute('type', 'file')
        elt.setAttribute('accept', 'application/json')
        elt.addEventListener('change', OpenFile)
        function OpenFile(event) {
            const input = event.target
            const reader = new FileReader()
            reader.onload = function () {
                const text = reader.result
                const obj = JSON.parse(text)
                resolve(obj)
            }
            reader.readAsText(input.files[0])
        }
        document.body.appendChild(elt)
        elt.click()
        document.body.removeChild(elt)
    })
}
