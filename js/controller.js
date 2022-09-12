window.addEventListener("load",init);
function init(){
    clearAll();
    loadId();
    showTotal();
    bindEvents();  
}

function clearAll(){
    /* this function clears the contents of the form except the ID (since ID is auto generated)*/
     document.querySelector('#name').value = ''
     document.querySelector('#price').value = ''
     document.querySelector('#desc').value = ''
     document.querySelector('#color').value = ''
     document.querySelector('#url').value = ''


}

let auto = autoGen();

function loadId(){
    /* t matically sets the value of ID */
    document.querySelector('#id').innerText = auto.next().value;
}

function showTotal(){
    /* this function populates the values of #total, #mark and #unmark ids of the form */
    document.querySelector('#total').innerText = itemOperations.items.length;
    document.querySelector('#mark').innerText = itemOperations.countTotalMarked();
    document.querySelector('#unmark').innerText = itemOperations.items.length - itemOperations.countTotalMarked();
}

function bindEvents(){
    document.querySelector('#remove').addEventListener('click',deleteRecords);
    document.querySelector('#add').addEventListener('click',addRecord);
    document.querySelector('#update').addEventListener('click',updateRecord)
    // document.querySelector('#exchange').addEventListener('change',getExchangerate)
    document.querySelector('#Save').addEventListener('click',Save)
    document.querySelector('#Load').addEventListener('click',Load)
}

function deleteRecords(){
    /* this function deletes the selected record from itemOperations
    and prints the table using the function printTable*/
    itemOperations.remove();
    printTable(itemOperations.items);
}

function addRecord(){
    /* this function adds a new record in itemOperations and then calls printRecord(). showTotal(), loadId() and clearAll()* /
     */
    //
    // import {
    //
    // } from "index.html";
    //


    console.log(document.querySelector('#id').innerText )
    console.log(document.querySelector('#name').value )
    console.log(document.querySelector('#price').value )
    console.log(document.querySelector('#desc').value )
    console.log(document.querySelector('#color').value )
    console.log(document.querySelector('#url').value )

    const id = document.querySelector('#id').innerText
    const name = document.querySelector('#name').value
    const price = document.querySelector('#price').value
    const desc = document.querySelector('#desc').value
    const color = document.querySelector('#color').value
    const url = document.querySelector('#url').value

    const item = new Item(id,name,price,desc,color,url)
    itemOperations.add(item)
    printRecord(item)
    showTotal()
    loadId()
    clearAll()

}

function edit(){
    /*this function fills (calls fillFields())
    the form with the values of the item to edit after searching it in items */
    const id = this.getAttribute("data-itemid")
    const item = itemOperations.search(id);
    fillFields(item);
}


function fillFields(itemObject){
    /*this function fills the form with the details of itemObject*/
    document.querySelector('#id').innerText = itemObject.id;
    document.querySelector('#name').value = itemObject.name;
    document.querySelector('#price').value = itemObject.price;
    document.querySelector('#desc').value = itemObject.desc;
    document.querySelector('#color').value = itemObject.color;
    document.querySelector('#url').value = itemObject.url;
}

function createIcon(className,fn, id){
 /* this function creates icons for edit and trash for each record in the table*/
    // <i class="fas fa-trash"></i>
    // <i class="fas fa-edit"></i>
    var iTag = document.createElement("i");
    iTag.className = className;
    iTag.addEventListener('click',fn);
    iTag.setAttribute("data-itemid", id) ;

    return iTag;
}


function updateRecord(){
    /*this function updates the record that is edited and then prints the table using printTable()*/
    const id = document.querySelector('#id').innerText
    const item = itemOperations.search(id);
    item.name = document.querySelector('#name').value
    item.price = document.querySelector('#price').value
    item.desc = document.querySelector('#desc').value
    item.color = document.querySelector('#color').value
    item.url = document.querySelector('#url').value
    printTable(itemOperations.items)
}

function trash(){
    /*this function toggles the color of the row when its trash button is selected and updates the marked and unmarked fields */
    let id = this.getAttribute('data-itemid');
    itemOperations.markUnMark(id);
    showTotal();
    let tr = this.parentNode.parentNode;
    tr.classList.toggle('alert-danger');
    console.log("I am Trash ",this.getAttribute('data-itemid'))
}

function printTable(items){
   /* this function calls printRecord for each item of items and then calls the showTotal function*/
    document.querySelector('#items').innerHTML = "";
    items.forEach(function(item){
        printRecord(item)
    })

    showTotal()
}
function printRecord(item){
    var tbody = document.querySelector('#items');
    var tr = tbody.insertRow();
    var index = 0;
    for(let key in item){
        if(key==='isMarked'){
            continue;
        }
        let cell = tr.insertCell(index);
        cell.innerText = item[key] ;
        index++;
    }
    var lastTD = tr.insertCell(index);
    lastTD.appendChild(createIcon('fas fa-trash mr-2',trash,item.id));
    lastTD.appendChild(createIcon('fas fa-edit',edit,item.id));
}

function getExchangerate(){
    /* this function makes an AJAX call to http://apilayer.net/api/live to fetch and display the exchange rate for the currency selected*/
    const key = "4zJSy38t7glDIreZ96Poy4H5kardl0Zo"
    const price = document.querySelector('#price').value;
    if(price.length === 0) { return }
    const i = document.querySelector('#exchange').selectedIndex;
    const country = document.querySelector('#exchange').options[i].value;
    const Header = new Headers()

    Header.append("apikey", key);

    var requestOptions = {
        method: 'GET',
        redirect: 'follow',
        headers: Header,
    };


    fetch(`https://api.apilayer.com/currency_data/convert?to=${country}&from=USD&amount=${price}`, requestOptions)
        .then(response => response.json())
        .then(json => {
            console.log(json);
            document.querySelector('#exrate').innerText = json.result })
        .catch(error => console.log('error', error));
}

function Save(){
    if (storageAvailable(`localStorage`)) {
        let items = itemOperations.items;
        const itemsJSON = JSON.stringify(items);
        localStorage.setItem("items", itemsJSON);
    } else {
        console.log('error')
    }

    if(localStorage.getItem('items')) {
        console.log('Yes' + localStorage.getItem('items'));
    } else {
        console.log('No');
    }

}

function Load(){
    let itemsJSON = localStorage.getItem("items");
    if(itemsJSON){
        itemOperations.items = JSON.parse(itemsJSON).map(function(item){
            return new Item(item.id, item.name, item.price, item.desc, item.color, item.url);
        });
        printTable(itemOperations.items);
        const maxed = Math.max(...itemOperations.items.map(function(item){
            return item.id;
        }))
        while(document.querySelector('#id').innerText <= maxed){
            loadId();
        }
    }else{
        return null;
    }

}

function storageAvailable(type) {
    try {
        const storage = window[type],
            x = '__storage_test__';
        storage.setItem(x, x);
        storage.removeItem(x);
        return true;
    }
    catch(e) {
        return false;
    }
}