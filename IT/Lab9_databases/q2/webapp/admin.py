from django.contrib import admin
from .models import Company, Person, Address


admin.site.register(Company)
admin.site.register(Person)
admin.site.register(Address)