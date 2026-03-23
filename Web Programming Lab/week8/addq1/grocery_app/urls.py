from django.urls import path
from . import views

urlpatterns = [
    # Maps the root URL of this app to the grocery_checklist view
    path("", views.grocery_checklist, name="grocery_checklist"),
]
