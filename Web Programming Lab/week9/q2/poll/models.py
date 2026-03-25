from django.db import models

class PollResult(models.Model):
    # We will use a single row in this table to track all votes for this specific question
    good_votes = models.IntegerField(default=0)
    satisfactory_votes = models.IntegerField(default=0)
    bad_votes = models.IntegerField(default=0)

    def __str__(self):
        return f"Poll Totals - Good: {self.good_votes}, Sat: {self.satisfactory_votes}, Bad: {self.bad_votes}"