from django import forms
from .models import Book


class BookForm(forms.ModelForm):
    class Meta:
        model = Book
        fields = ["title", "publication_date", "publisher", "authors"]
        # Adding HTML5 date picker widget for the date field
        widgets = {
            "publication_date": forms.DateInput(attrs={"type": "date"}),
        }
