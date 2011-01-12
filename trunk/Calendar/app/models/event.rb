# Table schema: (name:string, begin:integer, end:integer, location:string, extra_info:text, creator_id:integer)
# "begin", "end" are the timestamps for the beginning and end of this event.
# "location" might be an identifier in the future if we want to do location autocomplete.
# "identifier" might be added for the ease of adding an event with no invitation or recommendation.
# "searchable" might be added for enabling search. Currently, searching events is disabled.
class Event < ActiveRecord::Base
  belongs_to :creator, :class_name => "User"
  has_many :invitation, :dependent => :destroy
  has_many :recommendation, :dependent => :destroy
  has_many :acceptance, :dependent => :destroy
  has_many :reject, :dependent => :destroy
end
