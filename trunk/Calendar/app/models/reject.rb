# Table schema: event_id:integer, user_id:integer
class Reject < ActiveRecord::Base
  belongs_to :event
  belongs_to :user
end
