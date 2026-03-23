from django.urls import path
from . import views

urlpatterns = [
    path("", views.car_input, name="car_input"),
]
