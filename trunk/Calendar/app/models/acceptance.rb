# Table schema: (event_id:integer, user_id:integer)
class Acceptance < ActiveRecord::Base
  belongs_to :event
  belongs_to :user
end
