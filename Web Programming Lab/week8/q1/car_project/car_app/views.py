from django.shortcuts import render
from .forms import CarForm


def car_input(request):
    # If this is a POST request, we need to process the form data
    if request.method == "POST":
        form = CarForm(request.POST)
        if form.is_valid():
            # Extract the cleaned data from the form
            manufacturer = form.cleaned_data["manufacturer"]
            model_name = form.cleaned_data["model_name"]

            # Context to pass to the result page
            context = {"manufacturer": manufacturer, "model_name": model_name}
            # Forward the user to the result page with the parameters
            return render(request, "car_app/result.html", context)

    # If a GET (or any other method), create a blank form
    else:
        form = CarForm()

    # Render the input page
    return render(request, "car_app/index.html", {"form": form})
