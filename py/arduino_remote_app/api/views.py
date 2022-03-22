from django.shortcuts import render
from django.http import JsonResponse
from rest_framework.decorators import api_view
from .remote import query

# Used a lot from here: https://dev.to/nobleobioma/create-a-simple-rest-api-with-django-253p
# Create your views here.
@api_view(["GET"])
def volume_up(request):
    content = query("volume up")
    return JsonResponse(content)
