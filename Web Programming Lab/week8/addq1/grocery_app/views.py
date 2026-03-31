from django.shortcuts import render

GROCERY_ITEMS = {
    "Wheat": 40,
    "Jaggery": 50,
    "Dal": 80,
}


def grocery_checklist(request):
    selected_items_data = []

    if request.method == "POST":
        # request.POST.getlist() retrieves a list of all checked boxes with the name 'items'
        selected_item_names = request.POST.getlist("items")

        # Build a list of dictionaries containing the name and price of selected items
        for item in selected_item_names:
            if item in GROCERY_ITEMS:
                selected_items_data.append({"name": item, "price": GROCERY_ITEMS[item]})

    # Context passed to the template every time the page loads
    context = {
        "all_items": GROCERY_ITEMS.keys(),
        "selected_items": selected_items_data,
    }

    return render(request, "grocery_app/index.html", context)
