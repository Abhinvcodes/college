# college/urls.py
from django.urls import path
from . import views

urlpatterns = [
    path("", views.show_institutes, name="show_institutes"),
]
