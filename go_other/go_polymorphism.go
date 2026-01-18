package main

import "fmt"

type Sensor interface {
	Read() int
	SetConf(string)
}

type Sensor1234 struct {
	sensorId int
}

func (s Sensor1234) Read() int {
	return 123
}

func (s Sensor1234) SetConf(conf string) {

}

func ReadInterface(s Sensor) int {
	return s.Read()
}

func SetConfInterface(s Sensor, conf string) {
	s.SetConf(conf)
}

// composition
type SensorWithEmbedding struct {
	Sensor1234 
	sensorId int
}

func (s SensorWithEmbedding) Read() int {
	return 997
}

func main() {
	s1 := Sensor1234{sensorId: 1234}
	fmt.Println(ReadInterface(s1))
	SetConfInterface(s1, "conf")

	mp := make(map[Sensor]string)
	s2 := Sensor1234{sensorId: 4321}
	// if Sensor1234 won't have ID attribute then
	// go doesn't know how to distinguish keys so only one elem
	mp[s1] = "S1"
	mp[s2] = "S2"

	for _, k := range mp {
		fmt.Println(k)
	}

	fmt.Println(mp)

	s3 := SensorWithEmbedding{sensorId: 999, Sensor1234: Sensor1234{sensorId: 1234}}
	mp[s3] = "S3"
	fmt.Println(mp)

	// Embedding kill the feature that Base class can holds derived class
	// go doesn't have inheritance as other languages

	// Type with just an embedding polymorphism type can override virtual method 
	for obj, key := range mp {
		fmt.Println(key, obj.Read())
	}
}
