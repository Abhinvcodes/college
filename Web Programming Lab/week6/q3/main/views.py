from django.shortcuts import render

def home(request):
    return render(request, 'main/home.html')

def metadata(request):
    return render(request, 'main/metadata.html')

def reviews(request):
    return render(request, 'main/reviews.html')

def publisher(request):
    return render(request, 'main/publisher.html')