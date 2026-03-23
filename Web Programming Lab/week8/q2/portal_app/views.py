from django.shortcuts import render, redirect


def first_page(request):
    # If the user submits the form
    if request.method == "POST":
        # Store the submitted data in Django sessions
        request.session["name"] = request.POST.get("name")
        request.session["roll"] = request.POST.get("roll")
        request.session["subject"] = request.POST.get("subject")

        # Redirect to the second page
        return redirect("second_page")

    # If it's a normal page load (GET request), show the empty form
    return render(request, "portal_app/firstPage.html")


def second_page(request):
    # Retrieve the data from the session (with fallbacks if empty)
    context = {
        "name": request.session.get("name", "Not Provided"),
        "roll": request.session.get("roll", "Not Provided"),
        "subject": request.session.get("subject", "Not Provided"),
    }

    # Render the second page and pass the session data
    return render(request, "portal_app/secondPage.html", context)
