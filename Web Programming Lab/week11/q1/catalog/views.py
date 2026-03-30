from django.shortcuts import render, redirect
from .models import Book
from .forms import BookForm


def add_book(request):
    # If the user submits the form
    if request.method == "POST":
        form = BookForm(request.POST)
        if form.is_valid():
            form.save()  # Saves the book, including the FK and M2M relationships
            return redirect("book_list")  # Redirect to the retrieval page
    else:
        # If it's a GET request, just show the blank form
        form = BookForm()

    return render(request, "catalog/add_book.html", {"form": form})


def book_list(request):
    # Retrieve all books from the database
    # .prefetch_related() optimizes the database queries for the M2M authors
    books = Book.objects.select_related("publisher").prefetch_related("authors").all()
    return render(request, "catalog/book_list.html", {"books": books})
