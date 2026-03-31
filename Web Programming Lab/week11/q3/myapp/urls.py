from django.urls import path
from . import views

urlpatterns = [
    path("", views.index, name="index"),
    path("get/<int:id>/", views.get_details, name="get_details"),
    path("update/<int:id>/", views.update_human, name="update_human"),
    path("delete/<int:id>/", views.delete_human, name="delete_human"),
]
