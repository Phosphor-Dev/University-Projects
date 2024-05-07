const nums = [];

function getRandomColor() {
    var letters = '0123456789ABCDEF'.split('');
    var color = '#';
    for (var i = 0; i < 6; i++ ) {color += letters[Math.round(Math.random() * 15)];
    }
    document.getElementById("body").style.backgroundColor = color;
}

function generateListItems() {
    let items = "";
    for(let i = 0; i < nums.length; i++) {
      items += `<b>${nums[i]}</b><br></br>`;
    }
    return items;
  }

function displayArr(){
    document.getElementById('array').innerHTML = `
    <ol>
      ${generateListItems(nums)}
    </ol>
  `;
}

function addNum() {
    var num = Math.floor(Math.random() * 100) + 1
    nums.push(num);
    console.log(nums);
    displayArr();
}

function sort(){
    for(let i = 0; i < nums.length; i++){
        for(let j = 0; j < nums.length - i - 1; j++){
            if(nums[j + 1] < nums[j]){
                [nums[j + 1],nums[j]] = [nums[j],nums[j + 1]]
            }
        }
    };
    displayArr();
};