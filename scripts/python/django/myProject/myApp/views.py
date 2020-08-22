# myApp/views.py
from django.shortcuts import render
from django.http import HttpResponse
from myApp.models import Book

def detail(request):
    book_list = Book.objects.order_by('-pub_date')[:5]
    context = {'book_list': book_list}
    return render(request, 'myApp/detail.html', context)

# Create your views here.
def index(request):
    return HttpResponse("Hello, World!")