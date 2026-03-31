from django.shortcuts import render

def home_view(request):
    # Just displays the empty form on Page 1
    return render(request, 'shop/home.html')

def bill_view(request):
    if request.method == 'POST':
        # 1. Retrieve data from the form
        brand = request.POST.get('brand', 'Unknown Brand')
        # Use getlist() because checkboxes allow multiple selections
        selected_items = request.POST.getlist('items') 
        
        # Safely get the quantity, default to 0 if left blank
        try:
            quantity = int(request.POST.get('quantity', 0))
        except ValueError:
            quantity = 0

        # 2. Set up dummy prices and calculate the total
        price_list = {
            'Mobile': 500,
            'Laptop': 1000
        }
        
        total_amount = 0
        for item in selected_items:
            if item in price_list:
                # Multiply the price of the item by the quantity entered
                total_amount += price_list[item] * quantity

        # 3. Pass the formatted data to Page 2
        context = {
            'brand': brand,
            'items': ", ".join(selected_items), # Joins list into a readable string
            'quantity': quantity,
            'total_amount': total_amount
        }
        return render(request, 'shop/bill.html', context)
    
    # If someone tries to access /bill/ directly without submitting the form, send them back
    return render(request, 'shop/home.html')