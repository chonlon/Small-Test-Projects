package main

import (
	"fmt"
	"html/template"
	"log"
	"net/http"
	"strings"
)

func baseRouteHandlerFunc(w http.ResponseWriter, r *http.Request) {
	r.ParseForm()

	fmt.Println(r.Form)
	fmt.Println("path", r.URL.Path)
	fmt.Println("scheme", r.URL.Scheme)
	fmt.Println(r.Form["url_long"])

	for k, v := range r.Form {
		fmt.Println("key:", k)
		fmt.Println("val:", strings.Join(v, ""))
	}
	fmt.Fprintf(w, "Hello astaxie!")
}

func login(w http.ResponseWriter, r *http.Request) {
	fmt.Println("method:", r.Method)

	if r.Method == "GET" {
		t, _ := template.ParseFiles("login.gptl")
		log.Println(t.Execute(w, nil))
	} else {
		err := r.ParseForm()

		if err != nil {
			log.Fatal("ParseForm:", err)
		}

		fmt.Println("username:", r.Form["username"])
		fmt.Println("password:", r.Form["password"])
	}
}

func main() {
	http.HandleFunc("/", baseRouteHandlerFunc)
	http.HandleFunc("/login", login)

	err := http.ListenAndServe(":9000", nil)
	if err != nil {
		log.Fatal("ListenAndServer:", err)
	} else {
		log.Fatal("Server Start Successful!")
	}
}