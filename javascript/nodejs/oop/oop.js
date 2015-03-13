// This is a script that experiment with oop. The object here is a cat
var pets = [1];

var play = function playWith() {
    console.log("Trying to play");
    if (this.fullness === "hungry"){
	console.log(this.name + " is hungry and you tries to play with it, now it is angry");
    }
    if (this.emotion === "happy" || this.emotion === "sad"){
	console.log(this.name + " plays with you, " + this.name + " is happy now" );
	this.emotion = "happy";
    }
    else if (this.emotion === "angry"){
	console.log(this.name + " is angry, refules to play with you");
    }
}
    

function buyCat(name, colour, sex, emotion, fullness){
    pets[pets.length] = {
	name: name,
	colour: colour,
	sex: sex,
	emotion: emotion,
	fullness: fullness,
	playWith: play,
    }
}	

var cat =  {
    name: "May",
    colour: "black",
    sex: "female",
    emotion: "happy",
    fullness: "full",
    playWith: play
}
    
cat.playWith();

buyCat("Mary", "whilte", "male","sad", "hungry");

pets[1].playWith();
    
    
    
    
