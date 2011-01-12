# This file is auto-generated from the current state of the database. Instead
# of editing this file, please use the migrations feature of Active Record to
# incrementally modify your database, and then regenerate this schema definition.
#
# Note that this schema.rb definition is the authoritative source for your
# database schema. If you need to create the application database on another
# system, you should be using db:schema:load, not running all the migrations
# from scratch. The latter is a flawed and unsustainable approach (the more migrations
# you'll amass, the slower it'll run and the greater likelihood for issues).
#
# It's strongly recommended to check this file into your version control system.

ActiveRecord::Schema.define(:version => 20110111122412) do

  create_table "acceptances", :force => true do |t|
    t.integer  "event_id"
    t.integer  "user_id"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  create_table "adminships", :force => true do |t|
    t.integer  "group_id"
    t.integer  "user_id"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  create_table "events", :force => true do |t|
    t.string   "name"
    t.integer  "begin"
    t.integer  "end"
    t.string   "location"
    t.text     "extra_info"
    t.datetime "created_at"
    t.datetime "updated_at"
    t.integer  "creator_id"
  end

  create_table "groups", :force => true do |t|
    t.string   "name"
    t.string   "identifier"
    t.text     "extra_info"
    t.integer  "creator_id"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  create_table "invitations", :force => true do |t|
    t.integer  "event_id"
    t.text     "extra_info"
    t.datetime "created_at"
    t.datetime "updated_at"
    t.integer  "timestamp"
  end

  create_table "invitee_relations", :force => true do |t|
    t.integer  "user_id"
    t.integer  "invitation_id"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  create_table "invitor_relations", :force => true do |t|
    t.integer  "user_id"
    t.integer  "invitation_id"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  create_table "memberships", :force => true do |t|
    t.integer  "group_id"
    t.integer  "user_id"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  create_table "recommendations", :force => true do |t|
    t.integer  "event_id"
    t.integer  "group_id"
    t.integer  "admin_id"
    t.text     "extra_info"
    t.integer  "timestamp"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  create_table "rejects", :force => true do |t|
    t.integer  "event_id"
    t.integer  "user_id"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  create_table "users", :force => true do |t|
    t.string   "name"
    t.string   "email"
    t.string   "password"
    t.string   "mobile"
    t.text     "extra"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

end
