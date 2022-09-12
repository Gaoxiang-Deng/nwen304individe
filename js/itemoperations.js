
const itemOperations = {
    items:[],
    add(itemObject){
        /* adds an item into the array items*/
        this.items.push(itemObject)
    },
    remove(){
        // removes the item which has the "isMarked" field set to true*/
      this.items= this.items.filter(function(item){
         return !item.isMarked
      })
    },
    search(id){
        /* searches the item with a given argument id */
        for(let i in this.items){
            let item = this.items[i]
            if(item.id === id){
                return item;
            }
        }
    },
    markUnMark(id){
        /* toggle the isMarked field of the item with the given argument id*/
       this.search(id).toggle();
    },
    countTotalMarked(){
       /* counts the total number of marked items */
        let count = 0
        for(let i in this.items){
            let item = this.items[i]
            if(item.isMarked === true){
                count++;
            }
        }
       return count;
    },
   
}