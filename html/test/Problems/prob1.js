function addKeyValue(obj, key, value)
{
        obj[key] = value;
        return obj;
}
const obj = {name: "Adam"};
const newObj = addKeyValue(obj, "age", 25);
console.log(obj);
console.log(newObj);
