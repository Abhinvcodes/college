from django.shortcuts import render

def register_view(request):
    # Check if the form was submitted via POST (Secure method)
    if request.method == 'POST':
        # Safely retrieve data from the POST request
        username = request.POST.get('username')
        email = request.POST.get('email', 'Not provided')
        contact = request.POST.get('contact', 'Not provided')
        
        # We capture the password here but do not pass it to the success page for security
        password = request.POST.get('password') 

        # Package the data to send to the Success page
        context = {
            'username': username,
            'email': email,
            'contact': contact,
        }
        # Render the Success page directly with the submitted data
        return render(request, 'accounts/success.html', context)
    
    # If the request is a standard GET request, just display the empty Register form
    return render(request, 'accounts/register.html')