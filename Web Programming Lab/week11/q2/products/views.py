from django.shortcuts import render, redirect
from .models import Product
from .forms import ProductForm


# View to display the list of products
def index(request):
    products = Product.objects.all()
    return render(request, "products/index.html", {"products": products})


# View to handle the product entry form
def add_product(request):
    if request.method == "POST":
        form = ProductForm(request.POST)
        if form.is_valid():
            form.save()  # Saves the data to the database
            return redirect("index")  # Redirects back to the home page
    else:
        form = ProductForm()  # Creates an empty form for GET requests

    return render(request, "products/add_product.html", {"form": form})
