import json
from django.shortcuts import render, get_object_or_404
from django.http import JsonResponse
from .models import Human


def index(request):
    # Load only the humans for the initial dropdown
    humans = Human.objects.all()
    return render(request, "index.html", {"humans": humans})


def get_details(request, id):
    human = get_object_or_404(Human, pk=id)
    data = {
        "last_name": human.last_name,
        "phone": human.phone,
        "address": human.address,
        "city": human.city,
    }
    return JsonResponse(data)


def update_human(request, id):
    if request.method == "POST":
        data = json.loads(request.body)
        human = get_object_or_404(Human, pk=id)
        human.last_name = data.get("last_name")
        human.phone = data.get("phone")
        human.address = data.get("address")
        human.city = data.get("city")
        human.save()
        return JsonResponse({"status": "success"})


def delete_human(request, id):
    if request.method == "POST":
        human = get_object_or_404(Human, pk=id)
        human.delete()
        return JsonResponse({"status": "success"})
