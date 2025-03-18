function addOne(testArray)
{
        var addArray = [];
        for (let ii = 0; ii < testArray.length; ++ii)
        {
                addArray.push(testArray[ii] + 1);
        }
        return addArray;
}

const ages = [18, 22, 20, 25, 19, 30];
const newAges = addOne(ages);
console.log(newAges);
