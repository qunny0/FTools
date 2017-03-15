package common

import "fmt"

// HandleError haha zhejiu shi ge ceshi
//
func HandleError(err error, msg string) {
	if err == nil {
		return
	}
	fmt.Printf("error : %s\n", err.Error())
}
