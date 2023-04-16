from django.shortcuts import render
from django.http import JsonResponse
from rest_framework.decorators import api_view

import subprocess

from .remote import query


# Used a lot from here: https://dev.to/nobleobioma/create-a-simple-rest-api-with-django-253p
@api_view(["GET"])
def volume_up(request):
    content = query("volume up")
    return JsonResponse(content)

@api_view(["GET"])
def volume_down(request):
    return JsonResponse(query("volume down"))

@api_view(["GET"])
def power_toggle(request):
    return JsonResponse(query("power"))

@api_view(["GET"])
def restart_spotify(request):
    proc = subprocess.Popen("pkill spotify; sleep 1; gtk-launch spotify &")
    resp = dict(lines=[l for l, _ in zip(proc.stdout, range(10))])
    return JsonResponse(resp)
