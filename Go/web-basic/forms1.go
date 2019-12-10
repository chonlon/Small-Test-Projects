package main

import (
	"fmt"
	"html/template"
	"net/http"
)

type ContactDetails struct {
	Email string
	Subject string
	Message string
}

func main() {
	tmpl := template.Must(template.ParseFiles("forms.html"))

	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		tmpl.Execute(w, nil)
		details := ContactDetails {
			Email : r.FormValue("email"),
			Subject: r.FormValue("subject"),
			Message: r.FormValue("message"),
		}

		fmt.Print("%s %s %s", details.Email, details.Subject, details.Message)

		_ = details
		tmpl.Execute(w, struct {Success bool}{true})
	})
	http.ListenAndServe(":8080", nil)
}
