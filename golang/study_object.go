package main

import (
	"fmt"
)

// 继承
type Animal struct {
	Name string
	mean bool
}

type Dog struct {
	Animal
	BarkStrength int
}

type Cat struct {
	Basics       Animal
	MeowStrength int
}

// 封装
func (dog *Dog) MakeNoise() {
	barkStrength := dog.BarkStrength

	if dog.mean == true {
		barkStrength = barkStrength * 5
	}

	for bark := 0; bark < barkStrength; bark++ {
		fmt.Printf("BARK ")
	}

	fmt.Println("")
}

func (cat *Cat) MakeNoise() {
	meowStrength := cat.MeowStrength

	if cat.Basics.mean == true {
		meowStrength = meowStrength * 5
	}

	for meow := 0; meow < meowStrength; meow++ {
		fmt.Printf("MEOW ")
	}

	fmt.Println("")
}

// 多态
type AnimalSounder interface {
	MakeNoise()
}

func MakeSomeNoise(animalSounder AnimalSounder) {
	animalSounder.MakeNoise()
}

func main() {
	myDog := &Dog{
		Animal{
			"Rover", // Name
			false,   // mean
		},
		2, // BarkStrength
	}

	myCat := &Cat{
		Basics: Animal{
			Name: "Julius",
			mean: true,
		},
		MeowStrength: 3,
	}

	MakeSomeNoise(myDog)
	MakeSomeNoise(myCat)
}