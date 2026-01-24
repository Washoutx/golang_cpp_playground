package main

import (
	"io"
	"os"
)

// This task is specific for C++ because there is possibility to do RAII pattern
// This wrapper doesn't make any sense in golang but I wrote it just for exercise

type FileHandler struct {
	fd *os.File
}

func (fh *FileHandler) OpenFile(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	fh.fd = file
	return nil
}

func (fh *FileHandler) Close() error {
	if fh.fd != nil {
		err := fh.fd.Close()
		if err != nil {
			return err
		}
	}
	return nil
}

func main() {
	fh := FileHandler{}
	err := fh.OpenFile("test.txt")
	if err != nil {
		panic(err)
	}
	defer fh.Close()

	_, err2 := io.Copy(os.Stdout, fh.fd)
	if err2 != nil {
		panic(err2)
	}
}
