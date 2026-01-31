package main

import (
	"bufio"
	"fmt"
	"os"
	"path/filepath"
	"strconv"
)

func PrintProcesses() error {

	files, err := os.ReadDir("/proc")
	if err != nil {
		return err
	}

	for _, file := range files {
		if !file.IsDir() {
			continue
		}

		pid := file.Name()

		if _, err := strconv.Atoi(pid); err != nil {
			continue
		}

		commPath := filepath.Join("/proc", pid, "/comm")
		file, err := os.Open(commPath)
		if err != nil {
			continue
		}

		scanner := bufio.NewScanner(file)
		if scanner.Scan() {
			fmt.Printf("PID=%s | Name=%s\n", pid, scanner.Text())
		}

		file.Close()
	}

	return nil
}

func main() {
	PrintProcesses()
}
